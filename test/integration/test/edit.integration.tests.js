const assert = require('assert');
const util = require('util');

const exec = util.promisify(require('child_process').exec);

const {reset_env,setup_env} = require('./utils.js');

describe('edit integration tests', () => {

	/*
	 * This file should contain tests to test the full edit functionality,
	 * from parsing command line options and their interactions with editting files.
	 * Should also test behavior of edit which depends on state.
	 */

	beforeEach(async() => {
		await reset_env();
		await setup_env();
		await exec('git ex add hello.txt',{cwd:"/home/node/working"});
	});

	it('should succeed when editting a new file', async() => {
		await assert.doesNotReject(async() => {
			const res = await exec('git ex edit hello.txt',{cwd:"/home/node/working"});
			assert.deepStrictEqual(res,{stdout:'hello.txt saved\n',stderr:''});
		});
	});

	it('should delete temporary file after editting', async() => {
		await assert.doesNotReject(async() => {
			const res = await exec('git ex edit -v hello.txt',{cwd:"/home/node/working"});
			const index = res.stdout.indexOf("temporary file ");
			assert(index>-1);
			const tmp_filename = res.stdout.substr(index+15,11);
			await assert.rejects(async() => fs_stat(tmp_filename));
		});
	});

	after(async() => {
		await reset_env();
	});

});