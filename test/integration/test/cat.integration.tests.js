const assert = require('assert');
const util = require('util');

const exec = util.promisify(require('child_process').exec);

const {reset_env,setup_env} = require('./utils.js');

describe('cat integration tests', () => {

	/*
	 * This file should contain tests to test cat functionality
	 */

	beforeEach(async() => {
		await reset_env();
		await setup_env();
		await exec('git ex add hello.txt',{cwd:"/home/node/working"});
	});

	it('should cat successfully', async() => {
	 	await assert.doesNotReject(async() => {
	 		const res = await exec('git ex cat hello.txt',{cwd:"/home/node/working"});
	 		assert.deepStrictEqual(res,{stdout:'hello\n',stderr:''});
		});
	});

	it(`should fail when given a file which doesn't exist`, async() => {
		await assert.rejects(async() => await exec('git ex cat -b extra hello1.txt',{cwd:"/home/node/working"}));
	});

	it(`should fail when given a file which doesn't exist on the given branch`, async() => {
		await assert.rejects(async() => await exec('git ex cat -b notarealbranch hello1.txt',{cwd:"/home/node/working"}));
	});

	it('should cat successfully on the current branch', async() => {
	 	await assert.doesNotReject(async() => {
	 		const res = await exec('git ex cat -b master test.txt',{cwd:"/home/node/working"});
	 		assert.deepStrictEqual(res,{stdout:'test\n',stderr:''});
		});
	});

	after(async() => {
		await reset_env();
	});

});