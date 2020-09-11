const assert = require('assert');
const util = require('util');

const exec = util.promisify(require('child_process').exec);
const fs_stat = util.promisify(require('fs').stat);
const fs_readFile = util.promisify(require('fs').readFile);

const {reset_env,setup_env} = require('./utils.js');

describe('add integration tests', () => {

	/*
	 * This file should contain tests to test the full add functionality,
	 * from parsing command line options and their interactions with adding files.
	 * Should also test behavior of add which depends on state.
	 */

	beforeEach(async() => {
		await reset_env();
		await setup_env();	
	});

	it('should succeed when adding a new file', async() => {
		await assert.doesNotReject(async() => {
			const res = await exec('git ex add hello.txt',{cwd:"/home/node/working"});
			assert.deepStrictEqual(res,{stdout:'added hello.txt\n',stderr:''});
		});
	});

	it('should fail when not given a file', async() => {
		await assert.rejects(async() => await exec('git ex add',{cwd:"/home/node/working"}));
	});

	it('should succeed when given a valid template and verify template was applied', async() => {
		await assert.doesNotReject(async() => {
			const res = await exec('git ex add -t bug hello.txt',{cwd:"/home/node/working"});
			assert.deepStrictEqual(res,{stdout:'added hello.txt\n',stderr:''});

			const expected = (await fs_readFile("/usr/local/share/git-extra/templates/bug.template","utf8"))+"hello\n";
			const written = (await exec('git ex cat hello.txt',{cwd:"/home/node/working"})).stdout;

			assert.deepStrictEqual(expected,written);
		});
	});

	it(`should succeed when given a template which doesn't exist`, async() => {
		await assert.doesNotReject(async() => {
			const res = await exec('git ex add -t templatewhichdoesnotexist hello.txt',{cwd:"/home/node/working"});
			assert.deepStrictEqual(res,{stdout:'added hello.txt\n',stderr:''});

			const written = (await exec('git ex cat hello.txt',{cwd:"/home/node/working"})).stdout;
			assert.deepStrictEqual("hello\n",written);
		});
	});

	it('should fail when attempting to add a file that has already been added', async() => {
		await assert.doesNotReject(async() => {
			const res = await exec('git ex add hello.txt',{cwd:"/home/node/working"});
			assert.deepStrictEqual(res,{stdout:'added hello.txt\n',stderr:''});
			
			await assert.rejects(async() => await exec('git ex add hello.txt',{cwd:"/home/node/working"}));
		});
	});

	it('should delete temporary file after adding', async() => {
		await assert.doesNotReject(async() => {
			const res = await exec('git ex add -v hello.txt',{cwd:"/home/node/working"});
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