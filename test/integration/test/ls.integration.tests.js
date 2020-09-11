const assert = require('assert');
const util = require('util');

const exec = util.promisify(require('child_process').exec);

const {reset_env,setup_env} = require('./utils.js');

describe('ls integration tests', () => {

	/*
	 * This file should contain tests to test ls functionality.
	 */

	beforeEach(async() => {
		await reset_env();
		await setup_env();
		await exec('git ex add hello.txt',{cwd:"/home/node/working"});
		await exec('git ex add hello1.txt',{cwd:"/home/node/working"});
		await exec('mkdir test',{cwd:"/home/node/working"});
		await exec('git ex add test/hello.txt',{cwd:"/home/node/working"});
		await exec('mkdir -p test2/test',{cwd:"/home/node/working"});
		await exec('git ex add test2/test/hello.txt',{cwd:"/home/node/working"});
	});

	it('should ls successfully', async() => {
		await assert.doesNotReject(async() => {
			const res = await exec('git ex ls --long',{cwd:"/home/node/working"});

			let expected = '100644 blob ce013625030ba8dba906f756967f9e9ca394464a\thello.txt\n';
			expected += '100644 blob ce013625030ba8dba906f756967f9e9ca394464a\thello1.txt\n';
			expected += '100644 blob ce013625030ba8dba906f756967f9e9ca394464a\ttest/hello.txt\n';
			expected += '100644 blob ce013625030ba8dba906f756967f9e9ca394464a\ttest2/test/hello.txt\n';

			assert.deepStrictEqual(res,{stdout:expected,stderr:''});
		});
	});

	it('should ls (only names) successfully', async() => {
		await assert.doesNotReject(async() => {
			const res = await exec('git ex ls',{cwd:"/home/node/working"});

			let expected = 'hello.txt\n';
			expected += 'hello1.txt\n';
			expected += 'test/hello.txt\n';
			expected += 'test2/test/hello.txt\n';
			assert.deepStrictEqual(res,{stdout:expected,stderr:''});
		});
	});

	it('should ls inside a sub-directory successfully', async() => {
		await assert.doesNotReject(async() => {
			const res = await exec('git ex ls --long',{cwd:"/home/node/working/test"});

			const expected = '100644 blob ce013625030ba8dba906f756967f9e9ca394464a\thello.txt\n';
			assert.deepStrictEqual(res,{stdout:expected,stderr:''});
		});
	});

	it('should ls properly when not given any arguments', async() => {
		await assert.doesNotReject(async() => {
			const res = await exec('git ex',{cwd:"/home/node/working"});

			let expected = 'hello.txt\n';
			expected += 'hello1.txt\n';
			expected += 'test/hello.txt\n';
			expected += 'test2/test/hello.txt\n';
			assert.deepStrictEqual(res,{stdout:expected,stderr:''});
		});
	});

	after(async() => {
		await reset_env();
	});

});